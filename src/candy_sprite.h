#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <cmath>

using namespace godot;

//register class
class CandySprite : public Sprite2D {
	GDCLASS(CandySprite, Sprite2D);

	// Bobing feature
	bool enable_bob = true; // toggle to enable bobbing feature
	double height = 5.0;    // height/size of oscillation
	double bob_speed = 1.0; // the speed of osciallation
	double phase = 0.0;     // angle in rad used for sine wave
	int count_cycle = 0;    // how many sine cycles were completed
	Vector2 base_pos;       // starting postion we bob around

	// Spin feature
	bool enable_spin = false;     // toggle to enable spinning feature
	double spin_speed_deg = 30.0; // degrees per seconds

	// boost method (target method)
	double boost_factor = 1.0;    // multipliter used when boost is active
	double boost_time_left = 0.0; // remaining time left of boost

protected:
	static void _bind_methods() {
		// enable_bob
		ClassDB::bind_method(D_METHOD("set_enable_bob", "v"), &CandySprite::set_enable_bob);
		ClassDB::bind_method(D_METHOD("get_enable_bob"), &CandySprite::get_enable_bob);
		ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enable_bob"), "set_enable_bob", "get_enable_bob");

		// height
		ClassDB::bind_method(D_METHOD("set_height", "px"), &CandySprite::set_height);
		ClassDB::bind_method(D_METHOD("get_height"), &CandySprite::get_height);
		ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "height"), "set_height", "get_height");

		// bob_speed
		ClassDB::bind_method(D_METHOD("set_bob_speed", "hz"), &CandySprite::set_bob_speed);
		ClassDB::bind_method(D_METHOD("get_bob_speed"), &CandySprite::get_bob_speed);
		ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "bob_speed"), "set_bob_speed", "get_bob_speed");

		// enable_spin
		ClassDB::bind_method(D_METHOD("set_enable_spin", "v"), &CandySprite::set_enable_spin);
		ClassDB::bind_method(D_METHOD("get_enable_spin"), &CandySprite::get_enable_spin);
		ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enable_spin"), "set_enable_spin", "get_enable_spin");

		// spin_speed_deg
		ClassDB::bind_method(D_METHOD("set_spin_speed_deg", "deg_per_sec"), &CandySprite::set_spin_speed_deg);
		ClassDB::bind_method(D_METHOD("get_spin_speed_deg"), &CandySprite::get_spin_speed_deg);
		ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spin_speed_deg"), "set_spin_speed_deg", "get_spin_speed_deg");

		// bind methods called from godot
		ClassDB::bind_method(D_METHOD("apply_boost", "factor", "duration_sec"), &CandySprite::apply_boost);
		ClassDB::bind_method(D_METHOD("reset_base_position"), &CandySprite::reset_base_position);

		// integrate signal
		ADD_SIGNAL(MethodInfo("bob_cycle", PropertyInfo(Variant::INT, "count")));

	}

public:
	// setters and getters used by inspector
	void set_enable_bob(bool v) { enable_bob = v; }
	bool get_enable_bob() const { return enable_bob; }

	void set_height(double px) { height = px; }
	double get_height() const { return height; }

	void set_bob_speed(double hz) { bob_speed = hz; }
	double get_bob_speed() const { return bob_speed; }

	void set_enable_spin(bool v) { enable_spin = v; }
	bool get_enable_spin() const { return enable_spin; }

	void set_spin_speed_deg(double d) { spin_speed_deg = d; }
	double get_spin_speed_deg() const { return spin_speed_deg; }

	// lifecycle
	void _ready() override {
		base_pos = get_position();
	}

	void _process(double delta) override {
		// time-limited boost
		double mult = 1.0;
		if (boost_time_left > 0.0) {
			boost_time_left -= delta;
			if (boost_time_left <= 0.0) {
				boost_time_left = 0.0;
				boost_factor = 1.0;
			} else {
				mult = boost_factor;
			}
		}

		// if spin is enabled
		if (enable_spin) {
			double angle = get_rotation_degrees() + spin_speed_deg * mult * delta;
			angle = std::fmod(angle, 360.0);
			if (angle < 0.0) {
				angle += 360.0;
			}
			set_rotation_degrees(angle);
		}

		// if bob is enabled
		if (enable_bob) {
			constexpr double TWO_PI = 6.283185307179586476925286766559;
			phase += TWO_PI * (bob_speed * mult) * delta;

			if (phase >= TWO_PI) {
				phase = std::fmod(phase, TWO_PI);
				count_cycle++;
				emit_signal("bob_cycle", count_cycle);
			}

			double y_off = std::sin(phase) * height;
			set_position(Vector2(base_pos.x, base_pos.y + y_off));
		}
	}
	// temporarily speed up bobbing and spin for given amount of time
	void apply_boost(double factor, double duration_sec) {
		if (factor < 1.0) factor = 1.0;
		if (duration_sec < 0.0) duration_sec = 0.0;
		boost_factor = factor;
		boost_time_left = duration_sec;

	}
	// reset bob to sprite's current position
	void reset_base_position() {
		base_pos = get_position();
	}

};
