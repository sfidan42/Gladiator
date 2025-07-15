//
// Created by sadettin on 7/13/25.
//

#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <vector>
#include <glm/glm.hpp>
#include "animation/SpriteAnimator.h"
#include "datatypes/AnimatedFrames.h"

enum class Type2D { INTERFACE, NODE, VECTOR };

enum class Pos2D { FIXED, MOVING };

enum class Tex2D { IMAGE, SPRITE };

template <Tex2D>
struct Texture2DTraits;

template <>
struct Texture2DTraits<Tex2D::IMAGE> {
	using type = gImage;
};

template <>
struct Texture2DTraits<Tex2D::SPRITE> {
	using type = AnimatedFrames;
};

#define TEXTURE2D typename Texture2DTraits<tex>::type

template <Type2D type, Pos2D position, Tex2D texture>
class Object2D;

template <Pos2D position, Tex2D tex>
class Object2D<Type2D::INTERFACE, position, tex> {
public:
	Object2D(TEXTURE2D* _texture);
	virtual ~Object2D() = default;
	virtual glm::vec2 getPosition() const = 0;
	virtual glm::vec2 getMidPosition() const = 0;
	virtual glm::vec2 getSize() const = 0;
	virtual float getAngle() const = 0;
	virtual int getId() const = 0;
	virtual void draw() = 0;

	Object2D<Type2D::NODE, Pos2D::MOVING, tex>* getMovable();
	Object2D<Type2D::NODE, position, Tex2D::SPRITE>* getAnimated();

	TEXTURE2D* getTexture() const { return texture; }

	bool collision(float& outMarginLen, const glm::vec2& clickPos) const;

protected:
	TEXTURE2D* texture;
};

#include "datatypes/Object2DInterface.tpp"

template <Pos2D position, Tex2D tex>
class Object2D<Type2D::NODE, position, tex> : public Object2D<Type2D::INTERFACE, position, tex> {
public:
	Object2D(TEXTURE2D* texture,
	         const glm::vec2& targetPos, const glm::vec2& sourceSize,
	         float targetSizeScale = 1.0f, float targetAngle = 0.0f);

	template <Pos2D P = position, typename std::enable_if<P == Pos2D::MOVING, int>::type = 0>
	Object2D(const Object2D<Type2D::NODE, Pos2D::FIXED, tex>& ship);

	~Object2D();

	glm::vec2 getPosition() const { return pos; }
	glm::vec2 getMidPosition() const { return pos + size * 0.5f; }
	glm::vec2 getSize() const { return size; }
	float getAngle() const { return angle; }
	int getId() const { return id; }

	template <Tex2D T = tex, typename std::enable_if<T == Tex2D::SPRITE, int>::type = 0>
	void update(float deltaTime);

	template <Pos2D P = position, typename std::enable_if<P == Pos2D::MOVING, int>::type = 0>
	void move(const glm::vec2& stepSize, const glm::vec2& minBoundary, const glm::vec2& maxBoundary);

	void draw();

private:
	void drawImpl(std::integral_constant<Tex2D, Tex2D::IMAGE>);
	void drawImpl(std::integral_constant<Tex2D, Tex2D::SPRITE>);

	int id;
	glm::vec2 pos;
	glm::vec2 size;
	float angle;

	SpriteAnimator* animator;
};

#include "datatypes/Object2DNode.tpp"

template <Pos2D position, Tex2D tex>
class Object2D<Type2D::VECTOR, position, tex> {
	using TextureType = TEXTURE2D;

public:
	Object2D() = default;
	~Object2D();

	void update(float deltaTime);
	void draw() const;

	void addTexture(TextureType* texture);
	void addObject2D(size_t textureIndex,
	                 const glm::vec2& pos, const glm::vec2& size,
	                 float sizeScale = 1.0f, float angle = 0.0f);

	using it = typename std::vector<Object2D<Type2D::INTERFACE, position, tex>*>::iterator;
	it begin() { return children.begin(); }
	it end() { return children.end(); }
	Object2D<Type2D::INTERFACE, position, tex>* back() { return children.back(); }
	Object2D<Type2D::INTERFACE, position, tex>* front() { return children.front(); }
	void push_back(Object2D<Type2D::INTERFACE, position, tex>* obj) { children.push_back(obj); }
	void pop_back() { children.pop_back(); }

	it selectObject2D(const glm::vec2& clickPos);

private:
	std::vector<Object2D<Type2D::INTERFACE, position, tex>*> children;
	std::vector<TextureType*> texturelist;
};

#include "datatypes/Object2DVector.tpp"

#endif //OBJECT2D_H
