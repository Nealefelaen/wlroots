#ifndef WLR_TYPES_WLR_OUTPUT_LAYOUT_H
#define WLR_TYPES_WLR_OUTPUT_LAYOUT_H

#include <wlr/types/wlr_output.h>
#include <wayland-util.h>
#include <stdbool.h>

struct wlr_output_layout_state;

struct wlr_output_layout {
	struct wl_list outputs;
	struct wlr_output_layout_state *state;

	struct {
		struct wl_signal add;
		struct wl_signal change;
		struct wl_signal destroy;
	} events;
};

struct wlr_output_layout_output_state;

struct wlr_output_layout_output {
	struct wlr_output *output;
	int x, y;
	struct wl_list link;
	struct wlr_output_layout_output_state *state;

	struct {
		struct wl_signal destroy;
	} events;
};

struct wlr_output_layout *wlr_output_layout_create();

void wlr_output_layout_destroy(struct wlr_output_layout *layout);

struct wlr_output_layout_output *wlr_output_layout_get(
		struct wlr_output_layout *layout, struct wlr_output *reference);

struct wlr_output *wlr_output_layout_output_at(struct wlr_output_layout *layout,
		double x, double y);

void wlr_output_layout_add(struct wlr_output_layout *layout,
		struct wlr_output *output, int x, int y);

void wlr_output_layout_move(struct wlr_output_layout *layout,
		struct wlr_output *output, int x, int y);

void wlr_output_layout_remove(struct wlr_output_layout *layout,
		struct wlr_output *output);

/**
 * Given x and y as pointers to global coordinates, adjusts them to local output
 * coordinates relative to the given reference output.
 */
void wlr_output_layout_output_coords(struct wlr_output_layout *layout,
		struct wlr_output *reference, double *x, double *y);

bool wlr_output_layout_contains_point(struct wlr_output_layout *layout,
		struct wlr_output *reference, int x, int y);

bool wlr_output_layout_intersects(struct wlr_output_layout *layout,
		struct wlr_output *reference, int x1, int y1, int x2, int y2);

/**
 * Get the closest point on this layout from the given point from the reference
 * output. If reference is NULL, gets the closest point from the entire layout.
 */
void wlr_output_layout_closest_point(struct wlr_output_layout *layout,
		struct wlr_output *reference, double x, double y, double *dest_x,
		double *dest_y);

/**
 * Get the box of the layout for the given reference output. If `reference`
 * is NULL, the box will be for the extents of the entire layout.
 */
struct wlr_box *wlr_output_layout_get_box(
		struct wlr_output_layout *layout, struct wlr_output *reference);

/**
* Add an auto configured output to the layout. This will place the output in a
* sensible location in the layout. The coordinates of the output in the layout
* may adjust dynamically when the layout changes. If the output is already in
* the layout, it will become auto configured. If the position of the output is
* set such as with `wlr_output_layout_move()`, the output will become manually
* configured.
*/
void wlr_output_layout_add_auto(struct wlr_output_layout *layout,
		struct wlr_output *output);

/**
 * Get the output closest to the center of the layout extents.
 */
struct wlr_output *wlr_output_layout_get_center_output(
		struct wlr_output_layout *layout);

#endif
