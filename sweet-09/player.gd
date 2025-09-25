extends Node2D

@export var speed = 200 # How fast the player will move (pixels/sec).
@onready var hitbox: Area2D = $Hitbox
@onready var spr: AnimatedSprite2D = $AnimatedSprite2D
var screen_size # Size of the game window


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	screen_size = get_viewport_rect().size
	spr.play()
	spr.z_as_relative = false
	spr.z_index = 10
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	var velocity = Vector2.ZERO
	
	if Input.is_action_pressed("move_right"):
		velocity.x += 1
	if Input.is_action_pressed("move_left"):
		velocity.x -= 1
	if Input.is_action_pressed("move_up"):
		velocity.y -= 1
	if Input.is_action_pressed("move_down"):
		velocity.y += 1

		
	if velocity.length() > 0:
		velocity = velocity.normalized() * speed
		spr.play()
	else:
		spr.stop()
		
	if velocity.x != 0:
		spr.animation = "walk"
		spr.flip_v = false
		spr.flip_h = velocity.x < 0
	elif velocity.y != 0:
		spr.animation = "jump"
				
	position += velocity * delta
