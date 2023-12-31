#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void Pack(const std::string& files)
{
    std::vector<std::string> fileNames;
    std::stringstream ss(files);
    std::string fileName;

    while (std::getline(ss, fileName, ';'))
    {
        fileNames.push_back(fileName);
    }

    std::ofstream packedFile("pack.ap", std::ios::binary);

    if (packedFile.is_open())
    {
        for (const auto& file : fileNames)
        {
            std::ifstream input(file, std::ios::binary);

            if (input.is_open())
            {
                packedFile << "----------\n"; // разделитель секторов

                // Добавляем название файла в упакованный файл
                packedFile << file << "\n";

                // Копируем содержимое файла в упакованный файл
                packedFile << input.rdbuf();

                packedFile << "\n---------\n"; // разделитель секторов
                input.close();
            }
            else
            {
                std::cerr << "Unable to open file: " << file << std::endl;
            }
        }

        std::cout << "Packing complete. pack.ap has been created." << std::endl;

        packedFile.close();
    }
    else
    {
        std::cerr << "Unable to create pack.ap file." << std::endl;
    }
}

int main()
{
    std::cout << "AssetPacker 2023" << std::endl;
    std::cout << "Enter the names of the files to be packaged separated by ';' " << std::endl;
    std::string files;
    std::getline(std::cin, files);

    Pack(files);

    return 0;
}