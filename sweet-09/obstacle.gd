extends Area2D

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	area_entered.connect(func(a: Area2D):
		if a.is_in_group("player-hitbox"):
			get_tree().call_group("game", "lose_game", "Touched lava")
	)
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
