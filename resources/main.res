texture {
	name: bunny_colors
	src: textures/bunny_colors.png

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

	uniform: colorSampler = i[0]
}

material {
	name: bunny
	shader: simple

	texture: bunny_colors = 0
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
	name: bunny
	src: meshs/bunny.ob
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
