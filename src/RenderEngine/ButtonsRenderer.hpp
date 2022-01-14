/*
** EPITECH PROJECT, 2021
** B-YEP-400-MPL-4-1-indiestudio-cyril.grosjean
** File description:
** ButtonsRenderer
*/

#ifndef BUTTONSRENDERER_HPP_
#define BUTTONSRENDERER_HPP_

#include "../Buttons/Button.hpp"

namespace IS {
    class ButtonsRenderer {
        public:
            ButtonsRenderer();
            ~ButtonsRenderer();

            void addButton(int scene, Button *button);
            void init();

            void render(int scene);

        protected:
        private:
            std::map<int, std::vector<Button *>> _buttons;
    };
}

#endif /* !BUTTONSRENDERER_HPP_ */
