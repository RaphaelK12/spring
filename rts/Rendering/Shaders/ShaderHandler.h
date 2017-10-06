/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef SPRING_SHADERHANDLER_HDR
#define SPRING_SHADERHANDLER_HDR

#include <string>

#include "Rendering/GL/myGL.h" //GLuint
#include "System/UnorderedMap.hpp"

namespace Shader {
	struct IProgramObject;
	struct IShaderObject;
};

class CShaderHandler {
public:
	typedef spring::unsynced_map<std::string, Shader::IProgramObject*> ProgramObjMap;
	typedef spring::unsynced_map<std::string, Shader::IProgramObject*>::iterator ProgramObjMapIt;
	typedef spring::unsynced_map<std::string, ProgramObjMap> ProgramTable;

	static CShaderHandler* GetInstance();
	static void FreeInstance();

	void ReloadAll();
	bool ReleaseProgramObjects(const std::string& poClass, bool persistent = false);
	void ReleaseProgramObjectsMap(ProgramObjMap& poMap);

	Shader::IProgramObject* CreateProgramObject(const std::string& poClass, const std::string& poName, bool persistent = false);
	/**
	 * @param soName The filepath to the shader.
	 * @param soDefs Additional preprocessor flags passed as header.
	 * @param soType Can be GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, ...
	 */
	Shader::IShaderObject* CreateShaderObject(const std::string& soName, const std::string& soDefs, int soType);

	void ClearGameShaders();
	void ClearPersistentShaders();

	struct ShaderCache {
	public:
		void Clear() { cache.clear(); }

		unsigned int Find(unsigned int hash) {
			const auto it = cache.find(hash);

			GLuint id = 0;

			if (it != cache.end()) {
				id = it->second;
				cache.erase(it);
			}

			return id;
		}

		bool Push(unsigned int hash, unsigned int objID) {
			const auto it = cache.find(hash);

			if (it == cache.end()) {
				cache[hash] = objID;
				return true;
			}

			return false;
		}

	private:
		spring::unsynced_map<size_t, GLuint> cache;
	};

	const ShaderCache& GetShaderCache() const { return shaderCache; }
	      ShaderCache& GetShaderCache()       { return shaderCache; }

private:
	// game created programs, by name
	ProgramTable gameProgramObjects;
	// persistent (menu) created programs, by name
	ProgramTable persistentProgramObjects;

	// all (re)loaded program ID's, by hash
	ShaderCache shaderCache;
};

#define shaderHandler (CShaderHandler::GetInstance())

#endif
