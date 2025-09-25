extends Node2D
@export var target_score := 5

var score := 0

@onready var score_label: Label = $UI/scorelabel
@onready var pause: Control = $UI/pause
@onready var overviewlabel: Label = $UI/pause/overview

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	add_to_group("game")  # so Candy/Goo can call us
	pause.visible = false
	_update_ui()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func add_score(v: int) -> void:
	score += v
	_update_ui()
	if score >= target_score:
		win_game()

func win_game() -> void:
	overviewlabel.text = "You Win"
	pause.visible = true
	get_tree().paused = true

func lose_game(reason: String) -> void:
	overviewlabel.text = "You Lose"
	pause.visible = true
	get_tree().paused = true

func _update_ui() -> void:
	score_label.text = "Candy: %d / %d" % [score, target_score]
