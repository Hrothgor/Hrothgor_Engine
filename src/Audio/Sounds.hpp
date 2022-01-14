/*
** EPITECH PROJECT, 2021
** B-YEP-400-MPL-4-1-indiestudio-cyril.grosjean
** File description:
** Sounds
*/

#ifndef SOUNDS_HPP_
#define SOUNDS_HPP_

#include "../include.hpp"

namespace IS {
    class Sounds {
        public:
            Sounds(const std::string &soundPath, bool looping);
            ~Sounds();

            void play();
            void stop();

            void setLooping(bool loop);

            Music getMusic() const;

        protected:
        private:
            Music _music;
    };
}

#endif /* !SOUNDS_HPP_ */
