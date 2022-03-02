#include <SFML/Graphics.hpp>

class Screen {
    public:
        Screen();
        virtual void Init();
		virtual void Draw();
        virtual void ProcessInput();
        virtual int Update();
};