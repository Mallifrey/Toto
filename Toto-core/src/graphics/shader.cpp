#include "shader.h"
#include  "../other/globaldata.h"

namespace toto { namespace graphics {
	Shader::Shader(const char* vertPath, const char* fragPath)
		: m_VertPath(vertPath), m_FragPath(fragPath)
	{
		m_ShaderID = load();
	}
	
	Shader::~Shader(){
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::load(){
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

#if SHADER_COMPILED
		const char* vertSource = 
			"#version 410 core\n\
			#extension GL_ARB_separate_shader_objects : enable\n\
			\n\
			layout(location = 0) in vec4 position; \n\
			layout(location = 1) in vec4 color; \n\
			\n\
			uniform mat4 pr_matrix; \n\
			uniform mat4 vw_matrix = mat4(1.0); \n\
			uniform mat4 ml_matrix = mat4(1.0); \n\
			\n\
			out DATA{ \n\
			\n\
			vec4 position; \n\
			vec4 color; \n\
			\n\
			} vs_out; \n\
			\n\
			void main() {\n\
				gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n\
				vs_out.position = ml_matrix * position;\n\
				vs_out.color = color;\n\
			}";

		const char* fragSource = "#version 330 core\n\
			\n\
			layout(location = 0) out vec4 color;\n\
			\n\
			uniform vec4 colour; \n\
			uniform vec2 light_pos;\n\
			\n\
			in DATA{\n\
				vec4 position;\n\
				vec4 color;\n\
			} fs_in;\n\
			\n\
			void main() {\n\
				float intensity = 1.0f / length(fs_in.position.xy - light_pos);\n\
				//color = colour * intensity;\n\
				color = fs_in.color * intensity;\n\
			}";
#else
		std::string vertSourceString = read_file(m_VertPath);
		std::string fragSourceString = read_file(m_FragPath);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();
#endif


		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);
	
		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	
		if (result == GL_FALSE){
			GLint lenght;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &lenght);
			std::vector<char> error(lenght);
			glGetShaderInfoLog(vertex, lenght, &lenght, &error[0]);
			std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE){
			GLint lenght;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &lenght);
			std::vector<char> error(lenght);
			glGetShaderInfoLog(fragment, lenght, &lenght, &error[0]);
			std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	GLint Shader::getUniformLocation(const GLchar* name){
		return glGetUniformLocation(m_ShaderID, name);
	}

	void Shader::setUniform1f(const GLchar* name, float value){
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1fv(const GLchar* name, int count, float* value) {
		glUniform1fv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1i(const GLchar* name, int value){
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform1iv(const GLchar* name, int count, int* value) {
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector){
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector){
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector){
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix){
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	void Shader::enable() const {
		glUseProgram(m_ShaderID);
	}

	void Shader::disable() const {
		glUseProgram(0);
	}

}}