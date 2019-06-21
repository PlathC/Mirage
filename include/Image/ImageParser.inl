
namespace ImPro {
    namespace ImageParser{

        template<typename Type>
        Matrix<Type> FromPPM(std::string fileName)
        {
            std::vector<Type> result;

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

            std::getline(file, line);
            unsigned int height = 0, width = 0;
            if(std::regex_search(line, match, std::regex("([0-9]+)")))
            {
                std::stringstream streamConverter{match[0]};
                streamConverter >> width;
                streamConverter = std::stringstream{match[1]};
                streamConverter >> height;
            }

            std::getline(file, line);

            int index = 0;
            while(std::getline(file, line))
            {
                index++;
                Type t = Type();
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

            Matrix<Type> resultImg = Matrix<Type>( result, width, height);
            return resultImg;
        }


        template<typename Type>
        bool ToPPM(const Matrix<Type>& mat)
        {
            return false;
        }
    }
}