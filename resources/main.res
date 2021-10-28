texture {
	name: mice_colors
	src: textures/mice_colors.png

	format: RGB

	minFilter: NEAREST
	magFilter: NEAREST
}

texture {
	name: plant_colors
	src: textures/plant_colors.png

	format: RGB

	minFilter: NEAREST
	magFilter: NEAREST
}

texture {
	name: fox_colors
	src: textures/fox_colors.png

	format: RGB

	minFilter: NEAREST
	magFilter: NEAREST
}

////////////////////////////////

shader {
	name: simple
	src: shaders/simple.glsl

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

material {
	name: fox
	shader: simple

	texture: fox_colors = 0
}

///////////////////////////////////////////

mesh {
	name: mice
	src: meshs/mice.ob
}

mesh {
	name: fox
	src: meshs/fox.ob
}

mesh {
	name: plant
	src: meshs/plant.ob
}

mesh {
	name: ground
	src: meshs/ground.ob
}
