#include "Source/S3DGECommon.h"

int main()
{
	srand((uint)time(NULL));

	using namespace S3DGE;
	using namespace Maths;
	using namespace Graphics;

	Window window("S3DGE Test", 1280, 720, MODE_WINDOWED);
	window.SetVSync(false);

	Renderer2D renderer;
	mat4 ortho = mat4::GetOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Texture* textures[] =
	{
		new Texture("Box", "Resources\\box.jpg"),
		new Texture("Gradient","Resources\\gradient.bmp"),
		new Texture("Brick","Resources\\brick.jpg"),
	};

	std::vector<Renderable2D*> sprites;

	for (float y = 0; y < 9.0f; y += 0.5f)
		for (float x = 0; x < 16.0f; x += 0.5f)
		{
			if (rand() % 4 == 0)
			{

				int a = 255;
				int r = (int)(rand() % 1000 / 1000.0f * 255);
				int g = (int)(rand() % 1000 / 1000.0f * 255);
				int b = (int)(rand() % 1000 / 1000.0f * 255);

				uint color = a << 24 | b << 16 | g << 8 | r;

				sprites.push_back(new Sprite(x, y, 0.4f, 0.4f, color));
			}
			else
			{
				sprites.push_back(new Sprite(x, y, 0.4f, 0.4f, textures[rand() % 3]));
			}
		}

	int textureIDs[] = 
	{
		0,1,2,3,4,5,6,7,8,9
	};

	ShaderProgram shaderProgram("Resources\\basic.vs", "Resources\\basic.fs");
	shaderProgram.Enable();
	shaderProgram.SetUniform1iv("textureArray", 10, textureIDs);
	shaderProgram.SetUniformMat4fv("pr_matrix", ortho);

	int frames = 0;
	Timer t;

	while (!window.IsClosed())
	{
		window.Clear();

		shaderProgram.Enable();
		vec2f mouse = window.GetMousePosition();
		shaderProgram.SetUniform2f("light_pos", vec2f((float)(mouse.x * 16.0f / window.GetWidth()), (float)(9.0f - mouse.y * 9.0f / window.GetHeight())));
		
		renderer.Begin();
		for (uint i = 0; i < sprites.size(); i++)
			renderer.SubmitRenderable(sprites[i]);
		renderer.End();
		renderer.Flush();

		window.Update();
		
		++frames;
		if (t.ElapsedMS() > 1000.0f)
		{
			t.Start();
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	delete textures[0];
	delete textures[1];

	return 0;
}