#pragma once


template <Tex2D tex>
Object2DInterface<tex>::Object2DInterface(typename Texture2DTraits<tex>::type* _texture)
	: texture(_texture) {
}

template <Tex2D tex>
Object2D<Type2D::NODE, Pos2D::MOVING, tex>* Object2DInterface<tex>::getAlive() {
	return dynamic_cast<Object2D<Type2D::NODE, Pos2D::MOVING, tex>*>(this);
}

template <Tex2D tex>
const typename Texture2DTraits<tex>::type* Object2DInterface<tex>::getTexture() const {
	return texture;
}

template <Tex2D tex>
bool Object2DInterface<tex>::collision(float& outMarginLen, const glm::vec2& clickPos) const {
	outMarginLen = glm::length(clickPos - getMidPosition());
	return (outMarginLen <= glm::length(getSize() * 0.5f));
}

template <Pos2D position, Tex2D tex>
Object2D<Type2D::NODE, position, tex>::Object2D(typename Texture2DTraits<tex>::type* texture,
	const glm::vec2& targetPos, const glm::vec2& sourceSize, float targetSizeScale, float targetAngle)
    : Object2DInterface<tex>(texture), pos(targetPos), size(sourceSize * targetSizeScale), angle(targetAngle) {
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
	gLogi("Object2D<Type2D::NODE, position, tex>::Object2D") << "Created Object2D with id: " << this->id
		<< ", pos: " << pos.x << ", " << pos.y
		<< ", size: " << size.x << ", " << size.y
		<< ", angle: " << angle;
}

template <Pos2D position, Tex2D tex>
Object2D<Type2D::NODE, position, tex>::Object2D(Object2D& ship)
	: Object2DInterface<tex>(ship.getAnimatedFrames()) {
	static int sid;
	this->id = sid++;
	this->size = ship.getSize();
	this->pos = ship.getPosition();
	this->animator = new SpriteAnimator();
	auto* anim = new SpriteAnimation(Object2DInterface<tex>::texture);
	this->animator->addAnimation(anim);
}

template <Pos2D position, Tex2D tex>
Object2D<Type2D::NODE, position, tex>::~Object2D() {
    if(tex == Tex2D::IMAGE) {
        delete this->animator;
    }
}

template <Pos2D position, Tex2D tex>
glm::vec2 Object2D<Type2D::NODE, position, tex>::getPosition() const {
	return pos;
}

template <Pos2D position, Tex2D tex>
glm::vec2 Object2D<Type2D::NODE, position, tex>::getMidPosition() const {
	return pos + size * 0.5f;
}

template <Pos2D position, Tex2D tex>
glm::vec2 Object2D<Type2D::NODE, position, tex>::getSize() const {
	return size;
}

template <Pos2D position, Tex2D tex>
float Object2D<Type2D::NODE, position, tex>::getAngle() const {
	return angle;
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
	if (Object2DInterface<tex>::texture) {
		Object2DInterface<tex>::texture->draw(pos.x, pos.y, size.x, size.y, angle);
	}
}

// SPRITE
template <Pos2D position, Tex2D tex>
void Object2D<Type2D::NODE, position, tex>::drawImpl(std::integral_constant<Tex2D, Tex2D::SPRITE>) {
	if (animator) {
		animator->draw(pos, size, angle);
	}
}

template <Pos2D position, Tex2D tex>
Object2D<Type2D::VECTOR, position, tex>::~Object2D() {
	for(auto* child : children) {
		delete child;
	}
}

template <Pos2D position, Tex2D tex>
void Object2D<Type2D::VECTOR, position, tex>::update(float deltaTime) {
	for(auto* child : children) {
		auto* aliveChild = child->getAlive();
		if(aliveChild) {
			aliveChild->update(deltaTime);
		}
	}
}

template <Pos2D position, Tex2D tex>
void Object2D<Type2D::VECTOR, position, tex>::draw() const {
	for(auto* child : children) {
		child->draw();
	}
}

template <Pos2D position, Tex2D tex>
void Object2D<Type2D::VECTOR, position, tex>::addTexture(typename Texture2DTraits<tex>::type* texture) {
	texturelist.push_back(texture);
}

template <Pos2D position, Tex2D tex>
void Object2D<Type2D::VECTOR, position, tex>::addObject2D(size_t textureIndex,
	const glm::vec2& pos, const glm::vec2& size, float sizeScale, float angle) {
	using TextureType = typename Texture2DTraits<tex>::type;
	if (index >= texturelist.size()) {
		gLoge("Object2D<Type2D::VECTOR, position, tex>::addObject2D") << "Index out of bounds: " << index;
		return;
	}
	TextureType* texture = texturelist[index];
	auto* child = new Object2D<Type2D::NODE, position, tex>(texture, pos, size, sizeScale, angle);
	children.push_back(child);
}
