/*
** EPITECH PROJECT, 2022
** Physics_engine
** File description:
** LDL
*/

#ifndef LDL_HPP_
#define LDL_HPP_

#include <dlfcn.h>

namespace hr
{
    class LDL {
        public:
            static void *open(const char *path);
            static char *error();
            static void *sym(void *handle, const char *symbol);
            static int close(void *handle);
        protected:
        private:
    };
}

#endif /* !LDL_HPP_ */
