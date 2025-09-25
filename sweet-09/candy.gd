extends Area2D
@export var value := 1
@onready var visual := $Sprite2D
# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if visual:
		visual.connect("bob_cycle", Callable(self, "_on_bob_cycle"))  
	# enable connection
	area_entered.connect(func(a: Area2D):
		if a.is_in_group("player-hitbox"):
			# award points
			get_tree().call_group("game", "add_score", value)
			# boost all candies
			for c in get_tree().get_nodes_in_group("candies"):
				if c.has_method("apply_boost"):
					c.apply_boost(2.0, 1.5)
			queue_free()
	)
# signal handler: once every bob cycle
func _on_bob_cycle(count: int) -> void:
	print("%s bobbed cycles: %d" % [name, count])
