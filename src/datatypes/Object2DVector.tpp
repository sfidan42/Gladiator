#pragma once

template <Pos2D position, Tex2D tex>
Object2D<Type2D::VECTOR, position, tex>::~Object2D() {
	for(auto* child : children) {
		delete child;
	}
	for(auto* texture : texturelist) {
		delete texture;
	}
}

template <Pos2D position, Tex2D tex>
void Object2D<Type2D::VECTOR, position, tex>::update(float deltaTime) {
	for(auto* child : children) {
		auto* animatedChild = child->getAnimated();
		if(animatedChild) {
			animatedChild->update(deltaTime);
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
void Object2D<Type2D::VECTOR, position, tex>::addTexture(TEXTURE2D* texture) {
	texturelist.push_back(texture);
	gLogi("Object2D<Type2D::VECTOR, position, tex>::addTexture") << "Total textures: " << texturelist.size();
}

template <Pos2D position, Tex2D tex>
void Object2D<Type2D::VECTOR, position, tex>::addObject2D(size_t textureIndex,
	const glm::vec2& pos, const glm::vec2& size, float sizeScale, float angle) {
	using TextureType = TEXTURE2D;
	if (textureIndex >= texturelist.size()) {
		gLoge("Object2D<Type2D::VECTOR, position, tex>::addObject2D") << "Index out of bounds: " << textureIndex;
		return;
	}
	TextureType* texture = texturelist[textureIndex];
	auto* child = new Object2D<Type2D::NODE, position, tex>(texture, pos, size, sizeScale, angle);
	children.push_back(child);
}

template <Pos2D position, Tex2D tex>
typename std::vector<Object2D<Type2D::INTERFACE, position, tex>*>::iterator
Object2D<Type2D::VECTOR, position, tex>::selectObject2D(const glm::vec2& clickPos) {
	for (auto it = children.begin(); it != children.end(); ++it) {
		float marginLen;
		if ((*it)->collision(marginLen, clickPos)) {
			return it;
		}
	}
	return children.end();
}
