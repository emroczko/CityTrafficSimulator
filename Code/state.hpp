/**
 * state.hpp
 * Header of virtual class State.
 */

#pragma once

namespace zpr
{
    /**
     * Virtual class, from which every state of application inherits.
     */
    class State{
    public:
        virtual ~State() = default;
        virtual void init() = 0;
        virtual void handleInput() = 0;
        virtual void update(float dt) = 0;
        virtual void draw(float dt) = 0;
        virtual void pause()  { }
        virtual void resume()  { }
    };

}
