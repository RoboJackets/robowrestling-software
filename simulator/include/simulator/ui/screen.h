#include <SFML/Graphics.hpp>

class Screen {
    public:
        virtual void Init();
		virtual void Draw();
        virtual void ProcessInput();
        virtual void Update();
};