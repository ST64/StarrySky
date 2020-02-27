#ifndef STARRYSKY_MAP_HPP
#define STARRYSKY_MAP_HPP
#include <vector>
#include <string>
#include <random>
#include <sparsehash/dense_hash_map>
#include <GL/TextureAtlas.hpp>
#include <GL/Sprite.hpp>
#include <GL/Tilemap.hpp>
#include <GL/SpriteBatch.hpp>
#include <glm/glm.hpp>
#include <rapidjson/document.h>
enum WallType { LWALL=1, RWALL=2, CEIL=4, FLOOR=8, ONEWAY=16  };
struct Surface{
	Rect<float> hitbox;
	int flags;
};
struct MapSprite{
	glm::vec2 iPosition;
	std::string filename;
	Sprite spr;
};
class ObjMap {
public:
	ObjMap(const std::string& filename, TextureAtlas& atlas);
	void loadFromFile(const std::string& filename);
	void SetPosition(float x, float y);
	void Draw(SpriteBatch& frame);
	uint32_t addSurface(const Surface& wall);
	void addBGTexture(const glm::vec2& thisposition, const glm::mat2& transform, const std::string& fname);
	void WriteToFile(const std::string& filename);
	glm::vec2 position;
	google::dense_hash_map<int, Surface> surfaces;
	std::vector<glm::vec2> ledges; // top left corners
	std::mt19937 rng;
	int width = 1280;
	int height = 800;
	float ledgewidth = 8.f;
	float ledgeheight = 8.f;
	
private:
	google::dense_hash_map<std::string, TileMap> internal_tms;
	bool tm_changed = false;
	TextureAtlas& m_atlas;
	google::dense_hash_map<int, MapSprite> sprs;
	std::string loadTileMap(TileMap& tomodify, const rapidjson::Value& tilemapNode);
};
#endif
