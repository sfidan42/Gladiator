//
// Created by sadettin on 7/13/25.
//

#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <vector>
#include <glm/glm.hpp>
#include "animation/SpriteAnimator.h"
#include "datatypes/AnimatedFrames.h"

enum class Type2D { NODE, VECTOR };

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

template <Tex2D tex>
class Object2DInterface;

template <Type2D type, Pos2D position, Tex2D texture>
class Object2D;

template <Tex2D tex>
class Object2DInterface {
public:
	Object2DInterface(typename Texture2DTraits<tex>::type* _texture);
	virtual ~Object2DInterface() = default;
	virtual glm::vec2 getPosition() const = 0;
	virtual glm::vec2 getMidPosition() const = 0;
	virtual glm::vec2 getSize() const = 0;
	virtual float getAngle() const = 0;
	virtual void draw() = 0;
	Object2D<Type2D::NODE, Pos2D::MOVING, tex>* getAlive();
	const typename Texture2DTraits<tex>::type* getTexture() const;
	bool collision(float& outMarginLen, const glm::vec2& clickPos) const;
protected:
	typename Texture2DTraits<tex>::type* texture;
};

template <Pos2D position, Tex2D tex>
class Object2D<Type2D::NODE, position, tex> : public Object2DInterface<tex> {
public:
	Object2D(typename Texture2DTraits<tex>::type* texture, const glm::vec2& targetPos,
	         const glm::vec2& sourceSize, float targetSizeScale = 1.0f, float targetAngle = 0.0f);

	Object2D(Object2D& ship);

	~Object2D();

	glm::vec2 getPosition() const;
	glm::vec2 getMidPosition() const;
	glm::vec2 getSize() const;
	float getAngle() const;

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

template <Pos2D position, Tex2D tex>
class Object2D<Type2D::VECTOR, position, tex> {
	using TextureType = typename Texture2DTraits<tex>::type;
public:
	Object2D() = default;
	~Object2D();
	void update(float deltaTime);
	void draw() const;
	void addTexture(TextureType* texture);
	void addObject2D(size_t index,
		const glm::vec2& pos, const glm::vec2& size,
		float sizeScale = 1.0f, float angle = 0.0f);
private:
	std::vector<Object2DInterface<tex>*> children;
	std::vector<TextureType*> texturelist;
};

#include "datatypes/Object2D.tpp"
#endif //OBJECT2D_H
