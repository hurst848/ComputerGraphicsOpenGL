#include "camera.h"
#include "input.h"
#include <iostream>



glm::mat4 camera::getMatrix()
{
	glm::mat4 rtrn(1.0f);
	
	rtrn = glm::translate(rtrn, position);

	rtrn = glm::rotate(rtrn, glm::radians(yaw), glm::vec3(0,1,0));

	rtrn = glm::rotate(rtrn, glm::radians(pitch), glm::vec3(1, 0, 0));

	rtrn = glm::rotate(rtrn, glm::radians(roll), glm::vec3(0, 0, 1));
	

	return rtrn;
}

//glm::normalize
void camera::processInputs(input inp)
{
	//if (inp.getKey_e())
	//{
	//	roll -= 1.0f;
	//}
	//if (inp.getKey_q())
	//{
	//	roll += 1.0f;
	//}

	// mouse inputs and rotation
	if (inp.getKey_f())
	{
		float xoff = -inp.getMouseDelta().x * mouseSensitivity;
		float yoff = -inp.getMouseDelta().y * mouseSensitivity;

		yaw += xoff;	pitch += yoff;

		glm::vec3 frnt;
		frnt.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		frnt.y = sin(glm::radians(pitch));
		frnt.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		front = glm::normalize(frnt);
		right = glm::cross(frnt, up);

		glm::mat4 CameraModel(1.0f);


		CameraModel = glm::rotate(CameraModel, glm::radians(yaw), glm::vec3(0, 1, 0));

		CameraModel = glm::rotate(CameraModel, glm::radians(pitch), glm::vec3(1, 0, 0));

		CameraModel = glm::rotate(CameraModel, glm::radians(roll), glm::vec3(0, 0, 1));

		front = glm::vec3(CameraModel * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
		right = glm::vec3(CameraModel * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		up = glm::vec3(CameraModel * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));


		// keyboard inputs and position
		if (inp.getKey_w())
		{
			position += front * cameraSpeed;
		}
		if (inp.getKey_s())
		{
			position += -(front * cameraSpeed);
		}
		if (inp.getKey_a())
		{
			position += -(right * cameraSpeed);
		}
		if (inp.getKey_d())
		{
			position += right * cameraSpeed;
		}
		if (inp.getKey_space())
		{
			position += up * cameraSpeed;
		}
		if (inp.getKey_lControl())
		{
			position += -(up * cameraSpeed);
		}
	}


	
}
void camera::setTransform(glm::vec3 _position, glm::vec3 _rotation)
{
	position = _position;
	yaw = _rotation.x;
	pitch = _rotation.y;
	roll = _rotation.z;
}


/*glm::mat4 view(1.0f);

	float xoffset = -inp.getMouseDelta().x;
	float yoffset = inp.getMouseDelta().y;
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;
	yaw += xoffset;
	pitch += yoffset;

	glm::vec3 tmpdirection;
	tmpdirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	tmpdirection.y = sin(glm::radians(pitch));
	tmpdirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	glm::vec3 forward = glm::normalize(tmpdirection);

	glm::vec3 direction = glm::vec3(cos(glm::radians(yaw))  , 0 , sin(glm::radians(yaw)));

	glm::vec3 right = glm::cross(direction, glm::vec3(0.0f,1.0f,0.0f));
	glm::vec3 up = glm::cross(right, direction);

	if (inp.getKey_w()) { position += glm::normalize(right) * cameraSpeed; }
	else if (inp.getKey_s()) { position += glm::normalize(right) * -cameraSpeed; }
	else if (inp.getKey_a()) { position += direction * cameraSpeed; }
	else if (inp.getKey_d()) { position += direction * -cameraSpeed; }
	else if (inp.getKey_space()) { position += glm::normalize(up) * -cameraSpeed; }
	else if (inp.getKey_lControl()) { position += glm::normalize(up) * cameraSpeed; }


	view = glm::lookAt(position, position + forward, up);*/



	/*glm::vec3 forward = rotation;
	glm::vec3 right = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 up = glm::cross(forward, right);*/




	/*view = glm::rotate(view, glm::radians(rotation.x), glm::vec3(0,1,0)  );
	view = glm::rotate(view, glm::radians(-rotation.y), glm::vec3(1, 0, 0) );


	if (inp.getKey_w()) { position += glm::normalize(right) * cameraSpeed; }
	else if (inp.getKey_s()) { position += glm::normalize(right) * -cameraSpeed; }
	else if (inp.getKey_a()) { position += glm::normalize(forward) * cameraSpeed; }
	else if (inp.getKey_d()) { position += glm::normalize(forward) * -cameraSpeed; }
	else if (inp.getKey_space()) { position += glm::normalize(up) * -cameraSpeed; }
	else if (inp.getKey_lControl()) { position += glm::normalize(up) * cameraSpeed; }
	view = glm::translate(view, position);*/


	/*glm::vec3 direction = glm::vec3(
		glm::cos(glm::radians(rotation.x)) * glm::cos(glm::radians(rotation.y)),
		glm::sin(glm::radians(rotation.y)),
		glm::sin(glm::radians(rotation.x)) * glm::cos(glm::radians(rotation.y)));
	glm::vec3 forward = glm::normalize(direction);
	glm::vec3 right = glm::cross(forward, glm::vec3(0.0f,1.0f,0.0f));
	glm::vec3 up = glm::cross(forward, right);

	if (inp.getKey_w()) { position += glm::normalize(forward) * cameraSpeed; }
	else if (inp.getKey_s()) { position += -glm::normalize(forward) * cameraSpeed; }
	else if (inp.getKey_a()) { position += -glm::normalize(right) * cameraSpeed; }
	else if (inp.getKey_d()) { position += glm::normalize(right) * cameraSpeed; }
	else if (inp.getKey_space()) { position += glm::normalize(up) * cameraSpeed; }
	else if (inp.getKey_lControl()) { position += -glm::normalize(up) *cameraSpeed; }

	view = glm::lookAt(position, position + forward, up);
	*/
	//return view;