extends CharacterBody2D


const SPEED = 200.0
const JUMP_VELOCITY = -300.0
const ATTACK_COOLDOWN := 0.2

@onready var animated_sprite_2d: AnimatedSprite2D = $AnimatedSprite2D

var is_attacking := false
var attack_cooldown_left := 0.0

func _ready():
	animated_sprite_2d.sprite_frames.set_animation_loop("attack", false)
	animated_sprite_2d.animation_finished.connect(_on_animation_finished)

func _physics_process(delta):
	# Tick the cooldown down
	if attack_cooldown_left > 0.0:
		attack_cooldown_left -= delta

	# Gravity
	if not is_on_floor():
		velocity += get_gravity() * delta
	
	# Jump
	if Input.is_action_just_pressed("jump") and is_on_floor():
		velocity.y = JUMP_VELOCITY

	# Attack
	if Input.is_action_just_pressed("attack") and not is_attacking and attack_cooldown_left <= 0.0:
		is_attacking = true
		animated_sprite_2d.play("attack")
	
	# Movement 
	var direction := Input.get_axis("move_left", "move_right")
	if direction > 0:
		animated_sprite_2d.flip_h = false
	elif direction < 0:
		animated_sprite_2d.flip_h = true
	
	if direction:
		velocity.x = direction * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
		
	# Only play movement animations when not attacking
	if not is_attacking:
		if not is_on_floor():
			animated_sprite_2d.play("jump")
		elif direction == 0:
			animated_sprite_2d.play("idle")
		else:
			animated_sprite_2d.play("run")
	
	move_and_slide()

func _on_animation_finished():
	if animated_sprite_2d.animation == "attack":
		is_attacking = false
		attack_cooldown_left = ATTACK_COOLDOWN
