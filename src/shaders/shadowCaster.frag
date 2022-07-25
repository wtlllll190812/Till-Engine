#version 330 core
out vec4 color;
void main()
{             
    // gl_FragDepth = gl_FragCoord.z;
    color=vec4(gl_FragCoord.zzz,1.0);
}
// glm::mat4 Light::GetViewMatrix()
// {
// 	Transform* tr = gameobject->transform;
// 	return glm::lookAt(tr->position, glm::vec3(0), gameobject->transform->GetUp());
// }

// glm::mat4 Light::GetProjMatrix()
// {
// 	float near_plane = 1.0f, far_plane = 100.0f;
// 	return glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);
// }