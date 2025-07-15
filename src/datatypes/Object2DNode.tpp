#pragma once
#include "Object2DNode.h"

template <Pos2D position, Tex2D tex>
Object2D<Type2D::NODE, position, tex>::Object2D(TEXTURE2D* texture,
	const glm::vec2& targetPos, const glm::vec2& sourceSize, float targetSizeScale, float targetAngle)
    : Object2D<Type2D::INTERFACE, position, tex>(texture), pos(targetPos), size(sourceSize * targetSizeScale), angle(targetAngle) {
	static int sid;
	this->id = sid++;
	if (tex == Tex2D::IMAGE) {
		this->animator = nullptr;
	} else {
		this->animator = new SpriteAnimator();
		const auto* animatedFrames = dynamic_cast<const AnimatedFrames*>(texture);
		auto* anim = new SpriteAnimation(animatedFrames);
		this->animator->addAnimation(anim);
	}
	gLogi("Object2D<Type2D::NODE, Pos2D::" + gToStr(static_cast<int>(position)) + ", Tex2D::" + gToStr(static_cast<int>(tex)) + ">::Object2D")
		<< "Created Object2D with id: " << this->id
		<< ", pos: " << pos.x << ", " << pos.y
		<< ", size: " << size.x << ", " << size.y
		<< ", angle: " << angle;
}

template <Pos2D position, Tex2D tex>
template <Pos2D P, std::enable_if_t<P == Pos2D::MOVING, int>>
Object2D<Type2D::NODE, position, tex>::Object2D(const Object2D<Type2D::NODE, Pos2D::FIXED, tex>& object)
	: Object2D<Type2D::INTERFACE, position, tex>(object.getTexture()), angle(object.getAngle()) {
	static int sid;
	this->id = sid++;
	this->size = object.getSize();
	this->pos = object.getPosition();
	this->animator = new SpriteAnimator();
	auto* anim = new SpriteAnimation(Object2D<Type2D::INTERFACE, position, tex>::texture);
	this->animator->addAnimation(anim);
	gLogi("Object2D<Type2D::NODE, Pos2D::" + gToStr(static_cast<int>(position)) + ", Tex2D::" + gToStr(static_cast<int>(tex)) + ">::Object2D")
		<< "Copied Object2D with id: " << id
		<< ", pos: " << pos.x << ", " << pos.y
		<< ", size: " << size.x << ", " << size.y
		<< ", angle: " << angle;
}

template <Pos2D position, Tex2D tex>
Object2D<Type2D::NODE, position, tex>::~Object2D() {
    if(tex == Tex2D::IMAGE) {
        delete this->animator;
    }
}

template <Pos2D position, Tex2D tex>
template <Tex2D T, typename std::enable_if<T == Tex2D::SPRITE, int>::type>
void Object2D<Type2D::NODE, position, tex>::update(float deltaTime) {
	static_assert(tex == Tex2D::SPRITE, "update only valid for SPRITE");
	if (animator) {
		animator->update(deltaTime);
	}
}

template <Pos2D position, Tex2D tex>
template <Pos2D P, typename std::enable_if<P == Pos2D::MOVING, int>::type>
void Object2D<Type2D::NODE, position, tex>::move(const glm::vec2& stepSize, const glm::vec2& minBoundary, const glm::vec2& maxBoundary) {
	static_assert(position == Pos2D::MOVING, "move only valid for MOVING");
	pos = glm::clamp(pos + stepSize, minBoundary - size * 0.5f, maxBoundary - size * 0.5f);
}

// Draw with tag dispatch
template <Pos2D position, Tex2D tex>
void Object2D<Type2D::NODE, position, tex>::draw() {
	drawImpl(std::integral_constant<Tex2D, tex>());
}

// IMAGE
template <Pos2D position, Tex2D tex>
void Object2D<Type2D::NODE, position, tex>::drawImpl(std::integral_constant<Tex2D, Tex2D::IMAGE>) {
	if (Object2D<Type2D::INTERFACE, position, tex>::texture) {
		Object2D<Type2D::INTERFACE, position, tex>::texture->draw(pos.x, pos.y, size.x, size.y, angle);
	}
}

// SPRITE
template <Pos2D position, Tex2D tex>
void Object2D<Type2D::NODE, position, tex>::drawImpl(std::integral_constant<Tex2D, Tex2D::SPRITE>) {
	if (animator) {
		animator->draw(pos, size, angle);
	}
}
