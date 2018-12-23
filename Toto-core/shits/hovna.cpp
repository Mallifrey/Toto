
//#include <ctime>

std::srand(std::time(nullptr));
float number = rand() % 2;//
mat4 position = mat4::translation(vec3(2, 3, 4));
position *= mat4::identity();
vec4 column = position.columns[3];
std::cout << column.x << std::endl;



float red = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0))); //0 je min, 1 je max; v tomto pripade
float green = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
float blue = abs(red - green);

bool prev = false;

//std::cout << window.getWidth() << ", " << window.getHeight() << std::endl;
//std::cout << round(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX))) << std::endl;

double x, y;
window.getMousePosition(x, y);

if (window.isKeyPressed(GLFW_KEY_A)) {
	std::cout << "PRESSED" << std::endl;
}

if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
	std::cout << "X: " << x << ", Y: " << y << std::endl;
}

float r = 40;
float t = 30;
float right = 2 / r;
float top = 2 / t;


if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
	red = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
	green = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
	blue = abs(red - green);
}

if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && prev == false) {
	red = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
	green = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
	blue = abs(red - green);
	prev = true;
}
else if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
	prev = true;
}
else prev = false;

for (int x = 1; x <= r; x++) {
	for (int y = 1; y <= t; y++) {
		float barva = 0.0f;
		if ((x + y) % 2 == 0) {
			glBegin(GL_QUADS);
			glColor3f(red, green, blue);
			glVertex2f(-1.0f + right * (x - 1), 1.0f - top * (y - 1));
			glVertex2f(-1.0f + right * (x - 1), 1.0f - top * y);
			glVertex2f(-1.0f + right * x, 1.0f - top * y);
			glVertex2f(-1.0f + right * x, 1.0f - top * (y - 1));
			glEnd();
		}
	}
}










GLfloat vertices[] = {
	0, 0, 0,
	8, 0, 0,
	0, 4, 0,
	8, 4, 0
};

GLushort indeces[] = {
	0, 1, 2,
	1, 3, 2
};

GLfloat colorsA[] = {
	0.5f, 0, 1, 1,
	0.5f, 0, 1, 1,
	0.5f, 0, 1, 1,
	0.5f, 0, 1, 1,
};

GLfloat colorsB[] = {
	0.25f, 0, 0.5f, 1,
	0.25f, 0, 0.5f, 1,
	0.25f, 0, 0.5f, 1,
	0.25f, 0, 0.5f, 1
};

VertexArray sprite1, sprite2;
IndexBuffer ibo(indeces, 6);

sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
sprite1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);

sprite2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
sprite1.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);






glDrawArrays(GL_TRIANGLES, 0, 6);
//#else
sprite1.bind();
ibo.bind();

shader.setUniformMat4("ml_matrix", mat4::translation(vec3(6, 4, 0)));
glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

sprite1.unbind();
ibo.unbind();


sprite2.bind();
ibo.bind();

shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

sprite2.unbind();
ibo.unbind();





Simple2DRenderer renderer;


StaticSprite(x, y, 0.04f, 0.04f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1), shader)




mat4 mat = mat4::translation(vec3(5, 5, 5));
mat = mat * mat4::rotation(time.elapsed() * 10, vec3(1, 1, 1));
mat = mat * mat4::translation(vec3(-5, -5, -5));

// rotate ultra
mat4 mat = mat4::translation(vec3(width / 2, height / 2, 0));
mat = mat * mat4::rotation(time.elapsed() * 10.0f, vec3(1, 1, 1));
mat = mat * mat4::translation(vec3(-width / 2, -height / 2, 0));

shader.setUniformMat4("ml_matrix", mat);




shader.setUniformMat4("pr_matrix", ortho);
//shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3 ,0)));

BatchRenderer2D renderer;

std::vector<Renderable2D*> sprites;
srand(time(NULL));

for (float x = 0; x < rightb; x += 0.05f){
	for (float y = 0; y < topb; y += 0.05f){
		sprites.push_back(new Sprite(x, y, 0.035f, 0.035f, maths::vec4(rand() % 1000 / 1000.0f, 0, 0.5f, 1)));
	}
}

std::cout << "Sprites: " << sprites.size() << std::endl;

renderer.begin();

for (unsigned int i = 0; i < sprites.size(); i++) {
	renderer.submit(sprites[i]);
}

renderer.end();
renderer.flush();




Group* button = new Group(mat4::translation(maths::vec3(-15.0f, 5.0f, 0.0f)));
button->add(new Sprite(0, 0, 6.0f, 3.0f, vec4(1, 1, 1, 1)));
button->add(new Sprite(0.25f, 0.25f, 5.5f, 2.5f, vec4(0.5f, 1, 0, 1)));

Group* rotations = new Group(mat4::translation(vec3(1.5f, 0.45f, 0.0f)));
Group* rotate = new Group(mat4::rotation(45.0f, vec3(0, 0, 1)));

rotate->add(new Sprite(0, 0, 1.5f, 1.5f, maths::vec4(0.8f, 0.3f, 0.2f, 1)));
rotate->add(new Sprite(2.0f, -2.0f, 1.5f, 1.5f, maths::vec4(0.8f, 0.3f, 0.2f, 1)));

rotations->add(rotate);
button->add(rotations);
layer.add(button);










Shader& shader2 = *s2;
shader2.enable();
shader2.setUniform2f("light_pos", vec2(0, 0));


TileLayer layer2(&shader2);
layer2.add(new Sprite(-2, -2, 4, 4, vec4(0.8f, 0.2f, 0.8f, 1.0f)));

//shader.setUniform4f("colour", vec4(0, 0, 0, 1.0f));
//shader.setUniformMat4("vw_matrix", mat4::scale(vec3(1, 1, 1)));

shader2.enable();
shader2.setUniformMat4("ml_matrix", mat4::rotation(time.elapsed() * 100, vec3(1, 0, 1)));

layer2.render();






Texture* textures[] = {
	new Texture("src/img/test/1.png"),
	new Texture("src/img/test/2.png"),
	new Texture("src/img/test/3.png"),
	new Texture("src/img/test/4.png"),
	new Texture("src/img/test/5.png"),
	new Texture("src/img/test/6.png"),
	new Texture("src/img/test/7.png"),
	new Texture("src/img/test/8.png"),
	new Texture("src/img/test/9.png"),
	new Texture("src/img/test/10.png"),
	new Texture("src/img/test/11.png"),
	new Texture("src/img/test/12.png"),
	new Texture("src/img/test/13.png"),
	new Texture("src/img/test/14.png"),
	new Texture("src/img/test/15.png"),
	new Texture("src/img/test/16.png"),
	new Texture("src/img/test/17.png"),
	new Texture("src/img/test/18.png"),
	new Texture("src/img/test/19.png"),
	new Texture("src/img/test/20.png"),
	new Texture("src/img/test/21.png"),
	new Texture("src/img/test/22.png"),
	new Texture("src/img/test/23.png"),
	new Texture("src/img/test/24.png"),
	new Texture("src/img/test/25.png"),
	new Texture("src/img/test/26.png"),
	new Texture("src/img/test/27.png"),
	new Texture("src/img/test/28.png"),
	new Texture("src/img/test/29.png"),
	new Texture("src/img/test/30.png"),
	new Texture("src/img/test/31.png"),
	new Texture("src/img/test/32.png"),
	new Texture("src/img/test/33.png"),
	new Texture("src/img/test/34.png"),
	new Texture("src/img/test/35.png"),
	new Texture("src/img/test/36.png"),
	new Texture("src/img/test/37.png"),
	new Texture("src/img/test/38.png"),
	new Texture("src/img/test/39.png"),
	new Texture("src/img/test/40.png"),
	new Texture("src/img/test/41.png"),
	new Texture("src/img/test/42.png"),
	new Texture("src/img/test/43.png"),
	new Texture("src/img/test/44.png"),
	new Texture("src/img/test/45.png"),
	new Texture("src/img/test/46.png"),
	new Texture("src/img/test/47.png"),
	new Texture("src/img/test/48.png"),
	new Texture("src/img/test/49.png")
};