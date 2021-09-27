#include "game.h"
#include "view.h"

using namespace std::placeholders;

class AiController
{
public:
	AiController(View* v_, Snake* s_, Game* g_);
private:
	void update_direct();
       	View* v;
	Snake* s;
	Game* g;
};
