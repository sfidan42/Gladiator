#pragma once

template <Pos2D P, Tex2D TX>
Object2D<Type2D::INTERFACE, P, TX>::Object2D(typename Texture2DTraits<TX>::type* _texture)
	: texture(_texture) {
}

template <Pos2D P, Tex2D TX>
Object2D<Type2D::NODE, Pos2D::MOVING, TX>* Object2D<Type2D::INTERFACE, P, TX>::getMovable() {
	return dynamic_cast<Object2D<Type2D::NODE, Pos2D::MOVING, TX>*>(this);
}

template <Pos2D P, Tex2D TX>
Object2D<Type2D::NODE, P, Tex2D::SPRITE>* Object2D<Type2D::INTERFACE, P, TX>::getAnimated() {
	return dynamic_cast<Object2D<Type2D::NODE, P, Tex2D::SPRITE>*>(this);
}

template <Pos2D P, Tex2D TX>
bool Object2D<Type2D::INTERFACE, P, TX>::collision(float& outMarginLen, const glm::vec2& clickPos) const {
	outMarginLen = glm::length(clickPos - getMidPosition());
	return (outMarginLen <= glm::length(getSize() * 0.5f));
}
