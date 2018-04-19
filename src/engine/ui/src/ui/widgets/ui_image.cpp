#include "widgets/ui_image.h"

using namespace Halley;

UIImage::UIImage(Sprite s, Maybe<UISizer> sizer, Vector4f innerBorder)
	: UIWidget("", {}, sizer, innerBorder)
{
	setSprite(s);
}

void UIImage::draw(UIPainter& painter) const
{
	if (sprite.hasMaterial()) {
		painter.draw(sprite);
	}
}

void UIImage::update(Time t, bool moved)
{
	if (moved || dirty) {
		sprite
			.setPos(getPosition())
			.setScale(getSize() / (sprite.getRawSize().abs() + topLeftBorder + bottomRightBorder));
		dirty = false;
	}
}

void UIImage::setSprite(Sprite s)
{
	sprite = s;

	auto b = sprite.getOuterBorder();
	topLeftBorder = Vector2f(float(b.x), float(b.y));
	bottomRightBorder = Vector2f(float(b.z), float(b.w));
	auto c = s.getClip();
	
	auto spriteSize = (s.getRawSize().abs() + topLeftBorder + bottomRightBorder) * s.getScale();
	sprite.setAbsolutePivot(-topLeftBorder);
	
	if (c) {
		setMinSize(Vector2f::min(spriteSize, c.get().getSize()));
	} else {
		setMinSize(spriteSize);
	}
	dirty = true;
}

Sprite& UIImage::getSprite()
{
	return sprite;
}

const Sprite& UIImage::getSprite() const
{
	return sprite;
}
