#pragma once

template <Pos2D P, Tex2D TX>
Object2D<Type2D::VECTOR, P, TX>::~Object2D() {
	for(auto* child : children) {
		delete child;
	}
	for(auto* texture : texturelist) {
		delete texture;
	}
}

template <Pos2D P, Tex2D TX>
void Object2D<Type2D::VECTOR, P, TX>::update(float deltaTime) {
	for(auto* child : children) {
		auto* animatedChild = child->getAnimated();
		if(animatedChild) {
			animatedChild->update(deltaTime);
		}
	}
}

template <Pos2D P, Tex2D TX>
void Object2D<Type2D::VECTOR, P, TX>::draw() const {
	for(auto* child : children) {
		child->draw();
	}
}

template <Pos2D P, Tex2D TX>
void Object2D<Type2D::VECTOR, P, TX>::addTexture(typename Texture2DTraits<TX>::type* texture) {
	texturelist.push_back(texture);
	gLogi("Object2D<Type2D::VECTOR, P, TX>::addTexture") << "Total textures: " << texturelist.size();
}

template <Pos2D P, Tex2D TX>
void Object2D<Type2D::VECTOR, P, TX>::addObject2D(size_t textureIndex,
	const glm::vec2& pos, const glm::vec2& size, float sizeScale, float angle) {
	using TextureType = typename Texture2DTraits<TX>::type;
	if (textureIndex >= texturelist.size()) {
		gLoge("Object2D<Type2D::VECTOR, P, TX>::addObject2D") << "Index out of bounds: " << textureIndex;
		return;
	}
	TextureType* texture = texturelist[textureIndex];
	auto* child = new Object2D<Type2D::NODE, P, TX>(texture, pos, size, sizeScale, angle);
	children.push_back(child);
}

template <Pos2D P, Tex2D TX>
typename std::vector<Object2D<Type2D::INTERFACE, P, TX>*>::iterator
Object2D<Type2D::VECTOR, P, TX>::selectObject2D(const glm::vec2& clickPos) {
	auto selectedIt = children.end();
	float minMargin = std::numeric_limits<float>::max();
	for (auto it = children.begin(); it != children.end(); ++it) {
		float marginLen;
		if ((*it)->collision(marginLen, clickPos)) {
			if (marginLen < minMargin) {
				minMargin = marginLen;
				selectedIt = it;
			}
		}
	}
	return selectedIt;
}
