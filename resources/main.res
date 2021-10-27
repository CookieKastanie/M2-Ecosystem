texture {
	name: mice_colors
	src: mice_colors.png

	format: RGB

	minFilter: NEAREST
	magFilter: NEAREST
}

texture {
	name: plant_colors
	src: plant_colors.png

	format: RGB

	minFilter: NEAREST
	magFilter: NEAREST
}

////////////////////////////////

shader {
	name: simple
	src: simple.glsl

	uniform: albedo = i[0]
}

material {
	name: mice
	shader: simple

	texture: mice_colors = 0
}

material {
	name: plant
	shader: simple

	texture: plant_colors = 0
}

///////////////////////////////////////////

mesh {
	name: mice
	src: mice.ob
}

mesh {
	name: plant
	src: plant.ob
}

mesh {
	name: ground
	src: ground.ob
}
