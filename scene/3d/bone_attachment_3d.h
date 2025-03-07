/*************************************************************************/
/*  bone_attachment_3d.h                                                 */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef BONE_ATTACHMENT_H
#define BONE_ATTACHMENT_H

#include "scene/3d/skeleton_3d.h"

class BoneAttachment3D : public Node3D {
	GDCLASS(BoneAttachment3D, Node3D);

	bool bound = false;
	String bone_name;
	int bone_idx = -1;

	bool override_pose = false;
	int override_mode = 0;
	bool _override_dirty = false;

	enum OVERRIDE_MODES {
		MODE_GLOBAL_POSE,
		MODE_LOCAL_POSE,
		MODE_CUSTOM_POSE
	};

	bool use_external_skeleton = false;
	NodePath external_skeleton_node;
	ObjectID external_skeleton_node_cache;

	void _check_bind();
	void _check_unbind();

	void _transform_changed();
	void _update_external_skeleton_cache();
	Skeleton3D *_get_skeleton3d();

protected:
	virtual void _validate_property(PropertyInfo &property) const override;
	bool _get(const StringName &p_path, Variant &r_ret) const;
	bool _set(const StringName &p_path, const Variant &p_value);
	void _get_property_list(List<PropertyInfo> *p_list) const;
	void _notification(int p_what);

	static void _bind_methods();

public:
	String get_configuration_warning() const override;

	void set_bone_name(const String &p_name);
	String get_bone_name() const;

	void set_bone_idx(const int &p_idx);
	int get_bone_idx() const;

	void set_override_pose(bool p_override);
	bool get_override_pose() const;
	void set_override_mode(int p_mode);
	int get_override_mode() const;

	void set_use_external_skeleton(bool p_external_skeleton);
	bool get_use_external_skeleton() const;
	void set_external_skeleton(NodePath p_skeleton);
	NodePath get_external_skeleton() const;

	virtual void on_bone_pose_update(int p_bone_index);

	BoneAttachment3D();
};

#endif // BONE_ATTACHMENT_H
