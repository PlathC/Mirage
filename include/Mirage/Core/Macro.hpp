//
// Created by Cyprien Plateau--Holleville on 31/07/2019.
//

#ifndef MIRAGE_MACRO_HPP
#define MIRAGE_MACRO_HPP

#include <iostream>

#define MRG_UNUSED_PARAMETER(expr) do { (void)(expr); } while (0)
#define MRG_LOG(MESSAGE, ...) std::cout << "[MRG_LOG] " << __FILE__ << ":" << __LINE__ << " " \
                                << MESSAGE << __VA_ARGS__ << std::endl

#endif //MIRAGE_MACRO_HPP
