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

template <Pos2D>
struct Position2DTraits;
template <> struct Position2DTraits<Pos2D::FIXED> { using type = const glm::vec2; };
template <> struct Position2DTraits<Pos2D::MOVING> { using type = glm::vec2; };

template <Tex2D>
struct Texture2DTraits;
template <> struct Texture2DTraits<Tex2D::IMAGE> { using type = gImage; };
template <> struct Texture2DTraits<Tex2D::SPRITE> { using type = AnimatedFrames; };

template <Type2D TP, Pos2D P, Tex2D TX>
class Object2D;

template <Pos2D P, Tex2D TX>
class Object2D<Type2D::INTERFACE, P, TX> {
	using TextureType = typename Texture2DTraits<TX>::type;
public:
	Object2D(TextureType* _texture);
	virtual ~Object2D() = default;
	virtual glm::vec2 getPosition() const = 0;
	virtual glm::vec2 getMidPosition() const = 0;
	virtual glm::vec2 getSize() const = 0;
	virtual float getAngle() const = 0;
	virtual int getId() const = 0;
	virtual void draw() = 0;

	Object2D<Type2D::NODE, Pos2D::MOVING, TX>* getMovable();
	Object2D<Type2D::NODE, P, Tex2D::SPRITE>* getAnimated();

	TextureType* getTexture() const { return texture; }

	bool collision(float& outMarginLen, const glm::vec2& clickPos) const;

protected:
	TextureType* texture;
};

#include "datatypes/Object2DInterface.tpp"

template <Pos2D P, Tex2D TX>
class Object2D<Type2D::NODE, P, TX> : public Object2D<Type2D::INTERFACE, P, TX> {
	using TextureType = typename Texture2DTraits<TX>::type;
	using PositionType = typename Position2DTraits<P>::type;
public:
	Object2D(TextureType* texture,
	         const glm::vec2& targetPos, const glm::vec2& sourceSize,
	         float targetSizeScale = 1.0f, float targetAngle = 0.0f);

	template <Type2D TP2, Pos2D P2>
	Object2D(
		const Object2D<TP2, P2, TX>& object,
		std::enable_if_t<P == Pos2D::MOVING && (TP2 == Type2D::INTERFACE || TP2 == Type2D::NODE), int>* = nullptr
	);

	~Object2D();

	glm::vec2 getPosition() const { return pos; }
	glm::vec2 getMidPosition() const { return pos + size * 0.5f; }
	glm::vec2 getSize() const { return size; }
	float getAngle() const { return angle; }
	int getId() const { return id; }

	template <Tex2D tx = TX, std::enable_if_t<tx == Tex2D::SPRITE, int> = 0>
	void update(float deltaTime);

	template <Pos2D p = P, std::enable_if_t<p == Pos2D::MOVING, int> = 0>
	void move(const glm::vec2& stepSize, const glm::vec2& minBoundary, const glm::vec2& maxBoundary);

	template <Pos2D P2, Tex2D T2>
	void move(const Object2D<Type2D::NODE, P2, T2>* targetObject);

	void rotate(float angle);

	void draw();

private:

	void drawImpl(std::integral_constant<Tex2D, Tex2D::IMAGE>);
	void drawImpl(std::integral_constant<Tex2D, Tex2D::SPRITE>);

	int id;
	PositionType pos;
	PositionType size;
	float angle;

	SpriteAnimator* animator;
};

#include "datatypes/Object2DNode.tpp"

template <Pos2D P, Tex2D TX>
class Object2D<Type2D::VECTOR, P, TX> {
	using TextureType = typename Texture2DTraits<TX>::type;

public:
	Object2D() = default;
	~Object2D();

	void update(float deltaTime);
	void draw() const;

	void addTexture(TextureType* texture);
	void addObject2D(size_t textureIndex,
	                 const glm::vec2& pos, const glm::vec2& size,
	                 float sizeScale = 1.0f, float angle = 0.0f);

	using it = typename std::vector<Object2D<Type2D::INTERFACE, P, TX>*>::iterator;
	it begin() { return children.begin(); }
	it end() { return children.end(); }
	Object2D<Type2D::INTERFACE, P, TX>* back() { return children.back(); }
	Object2D<Type2D::INTERFACE, P, TX>* front() { return children.front(); }
	void push_back(Object2D<Type2D::INTERFACE, P, TX>* obj) { children.push_back(obj); }
	void pop_back() { children.pop_back(); }

	it selectObject2D(const glm::vec2& clickPos);

private:
	std::vector<Object2D<Type2D::INTERFACE, P, TX>*> children;
	std::vector<TextureType*> texturelist;
};

#include "datatypes/Object2DVector.tpp"

#endif //OBJECT2D_H
