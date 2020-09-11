#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H
#include <vector>
#include <string>
#include <string_view>
#include <util/Rect.hpp>
#include <util/Bitmask.hpp>
#include <GL/Texture.hpp>

/* Class for loading .bin.gz files and associated .dds.gz files, generated by crunch */
struct Atlas{
	std::unordered_map<std::string, Texture> m_texture_table;
	uint32_t m_texture = 0;
	uint32_t format = 0;
	uint16_t width=0, height=0;
};
class TextureAtlas{
public:
	explicit TextureAtlas(const std::string_view file_path);
	const Texture findSubTexture(const std::string& name) const;
//	const Bitmask& getBitmask(const Texture& tex) const;
	std::vector<std::string> getSubTextureNames() const;
	~TextureAtlas();
	std::vector<uint32_t> m_texture_handles;
private:
	std::vector<Atlas> m_atlas_list;
	std::unordered_map<uint32_t, Bitmask> Bitmasks;
	bool loadDDSgz(const std::string_view path, Atlas& atlas);
	bool loadBINgz(const std::string_view path, const Atlas& atlas);
};

#endif
