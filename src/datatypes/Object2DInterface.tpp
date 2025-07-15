#pragma once

template <Pos2D position, Tex2D tex>
Object2D<Type2D::INTERFACE, position, tex>::Object2D(TEXTURE2D* _texture)
	: texture(_texture) {
}

template <Pos2D position, Tex2D tex>
Object2D<Type2D::NODE, Pos2D::MOVING, tex>* Object2D<Type2D::INTERFACE, position, tex>::getMovable() {
	return dynamic_cast<Object2D<Type2D::NODE, Pos2D::MOVING, tex>*>(this);
}

template <Pos2D position, Tex2D tex>
Object2D<Type2D::NODE, position, Tex2D::SPRITE>* Object2D<Type2D::INTERFACE, position, tex>::getAnimated() {
	return dynamic_cast<Object2D<Type2D::NODE, position, Tex2D::SPRITE>*>(this);
}

template <Pos2D position, Tex2D tex>
bool Object2D<Type2D::INTERFACE, position, tex>::collision(float& outMarginLen, const glm::vec2& clickPos) const {
	outMarginLen = glm::length(clickPos - getMidPosition());
	return (outMarginLen <= glm::length(getSize() * 0.5f));
}
