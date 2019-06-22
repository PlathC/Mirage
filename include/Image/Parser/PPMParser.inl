#include <regex>

namespace ImPro {
    namespace ImageParser{
        template<typename T>
        Matrix<T> PPMParser<T>::Parse(std::string fileName)
        {
            std::vector<T> result;

            std::regex pattern;
            std::smatch match;
            std::ifstream file { fileName };
            std::string line { "" };

            // Format acquisition
            std::getline(file, line);

            if(line.find("P1") != std::string::npos)
            {
                throw std::runtime_error("This features isn't implemented.");
            }else if(line.find("P2") != std::string::npos)
            {
                throw std::runtime_error("This features isn't implemented.");
            }else if(line.find("P3") != std::string::npos)
            {
                pattern = std::regex{"([0-9]+)\\s([0-9]+)\\s([0-9]+)"};
            }

            // Size acquisition
            std::getline(file, line);
            unsigned int height = 0, width = 0;
            if(std::regex_search(line, match, std::regex("([0-9]+)\\s([0-9]+)")))
            {
                width = std::stoi(match[1]);
                height = std::stoi(match[2]);
            }


            // Skip number format (temporary)
            std::getline(file, line);

            // Data acquisition
            int index = 0;
            while(std::getline(file, line))
            {
                index++;
                T t = T(255, 255, 255);
                if(std::regex_search(line, match, pattern))
                {
                    t[0] = std::stod(match[0]);
                    t[1] = std::stod(match[1]);
                    t[2] = std::stod(match[2]);

                    result.push_back(t);
                } else {
                    result.push_back(t);
                }
            }

            Matrix<T> resultImg = Matrix<T>( result, width, height);
            return resultImg;
        }

        template<typename T>
        void PPMParser<T>::Write(Matrix<T>& mat, std::string fileName)
        {
            std::ofstream file { fileName };

            file << "P3" << std::endl;
            file << mat.Width() << " " << mat.Height() << std::endl;
            file << "255" << std::endl;
            std::vector<T> data = mat.GetData();

            for(auto it = data.begin(); it != data.end(); ++it) {
                file << *it << std::endl;
            }
        }
    }
}