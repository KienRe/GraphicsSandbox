#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Debug.h"

class Shader
{
public:
	unsigned int ID;

	Shader()
	{

	}

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR:SHADER::FRAGEMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		glCheckError();
	}

	void use()
	{
		glUseProgram(ID);

		glCheckError();
	}

	void setBool(const std::string &name, bool value) const
	{
		GLuint loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1) std::cout << "ERROR::SHADER::SETBOOL::" << name << "::LOCATION_NOT_FOUND\n" << std::endl;
		glUniform1i(loc, (int)value);

		glCheckError();
	}

	void setInt(const std::string &name, int value) const
	{
		GLuint loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1) std::cout << "ERROR::SHADER::SETINT::" << name << "::LOCATION_NOT_FOUND\n" << std::endl;
		glUniform1i(loc, value);

		glCheckError();
	}

	void setFloat(const std::string &name, float value) const
	{
		GLuint loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1) std::cout << "ERROR::SHADER::SETFLOAT::" << name << "::LOCATION_NOT_FOUND\n" << std::endl;
		glUniform1f(loc, value);

		glCheckError();
	}

	void setMat4(const std::string &name, glm::mat4 value) const
	{
		GLuint loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1) std::cout << "ERROR::SHADER::SETMAT4::" << name << "::LOCATION_NOT_FOUND\n" << std::endl;
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));

		glCheckError();
	}

	void setVec3(const std::string& name,glm::vec3 value) const
	{
		GLuint loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1) std::cout << "ERROR::SHADER::SETVEC3::" << name << "::LOCATION_NOT_FOUND\n" << std::endl;
		glUniform3f(loc, value.x, value.y, value.z);

		glCheckError();
	}

	void setVec3(const std::string& name, float x, float y, float z) const
	{
		GLuint loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1) std::cout << "ERROR::SHADER::SETVEC3::" << name << "::LOCATION_NOT_FOUND\n" << std::endl;
		glUniform3f(loc, x, y, z);

		glCheckError();
	}
};