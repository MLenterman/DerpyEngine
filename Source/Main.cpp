#include <memory>

#include "Graphics/Window.h"
#include "Graphics/Shaders/Shader.h"
#include "Maths/Maths.h"
#include "Utils/timer.h"
#include "Graphics/Layers/Layer.h"
#include "Graphics/Rendering/Renderer2D.h"
#include "Graphics/Rendering/BatchRenderer2D.h"
#include "Graphics/Sprites/Sprite.h"
#include "Graphics/Buffers/Buffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Layers/Group.h"
//#include "Graphics/font_manager.h"
//#include "Graphics/label.h"
//#include "Graphics/Textures/Texture.h"
//#include "Audio/sound_manager.h"
//#include "TileLayer.h"
int main(){
	using namespace Derpy;
	using namespace Graphics;
	using namespace Maths;
	Window window("Derpy!", 960, 540);
	//glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	Mat4f ortho = Mat4f::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
	Mat4f proj = Mat4f::perspective(70.0f, 0.7f, 0.1f, 100.0f);
	Shader* s = new Shader("Resources/Shaders/Basic.vert", "Resources/Shaders/Basic.frag");
	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", Vec2f(4.0f, 1.5f));
	shader.setUniform4f("colour", Vec4f(0.2f, 0.3f, 0.8f, 1.0f));
	shader.setUniformMat4("pr_matrix", ortho);

	srand(time(NULL));

	BatchRenderer2D* renderer = new BatchRenderer2D();

	Layer layer(renderer, &shader, ortho);
	for (float y = -9.0f; y < 9.0f; y += 0.1){
		for (float x = -16.0f; x < 16.0f; x += 0.1){
			int b = rand() % 255;
			int g = rand() % 255;
			int r = rand() % 255;
			unsigned int col = 255 << 24 | b << 16 | g << 8 | r;
			layer.add(new Sprite(x, y, 0.09f, 0.09f, col));
		}
	}

	Utils::Timer time;
	float timer = 0;
	unsigned int frames = 0;
	std::vector<Renderable2D*> sprites = layer.getRenderables();
	window.clear();
	window.update();

	Vec3f zoom(1.0f, 1.0f, 1.0f);
	Mat4f zoomMatrix = Mat4f::scale(zoom);
	while (!window.isClosed()){
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		
		if (window.isKeyTyped(333)){
			zoom.z += 0.01f;
			zoomMatrix = Mat4f::scale(zoom);
		}

		shader.setUniformMat4("pr_matrix", ortho *= zoomMatrix);
			

		layer.render();
		window.update();
		shader.setUniform2f("light_pos", Vec2f((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
		frames++;
		if (time.elapsed() - timer > 1.0f){
			timer += 1.0f;
			std::cout << "FPS: " << frames << std::endl;
			std::cout << "Sprites: " << sprites.size() << std::endl;
			std::vector<Vec2f> uv = sprites[0]->getUV();
			std::cout << "UV: " << std::endl;
			for (int i = 0; i < uv.size(); i++){
				std::cout << uv[i].x << ", " << uv[i].y << std::endl;
			}
			frames = 0;
		}
	}

	return 0;
}