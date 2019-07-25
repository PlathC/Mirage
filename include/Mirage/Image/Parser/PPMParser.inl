#include <regex>

namespace mrg {
    namespace ImageParser{
        template<typename T>
        Matrix<T> PPMParser<T>::Parse(std::string fileName, const unsigned int channel)
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
                width = static_cast<unsigned int>(std::stoi(match[1]));
                height = static_cast<unsigned int>(std::stoi(match[2]));
            }

            // Skip number format (temporary)
            std::getline(file, line);

            // Data acquisition
            int index = 0;
            while(std::getline(file, line))
            {
                index++;
                T t;
                if constexpr(std::is_arithmetic<T>::value)
                {
                    t = T(255);
                }
                else
                {
                    t = T();
                    for(unsigned int i = 0; i < channel; i++)
                        t[i] = 255;
                }

                if(std::regex_search(line, match, pattern))
                {
                    if constexpr(std::is_arithmetic<T>::value)
                    {
                        t = std::stod(match[0]);
                    }
                    else
                    {
                        t[0] = std::stod(match[0]);
                        t[1] = std::stod(match[1]);
                        t[2] = std::stod(match[2]);
                    }

                    result.push_back(t);
                } else {
                    result.push_back(t);
                }
            }

            Matrix<T> resultImg = Matrix<T>( result, width, height, channel);
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