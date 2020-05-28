using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMovement : MonoBehaviour
{
    private float CameraSpeed = 20f;
    private Vector3 pos;

    float xRotation = 0f;
    float yRotation = 0f;

    float MouseSpeed = 150f;

    public CharacterController controller;

    // Start is called before the first frame update
    void Start()
    {
        xRotation = Camera.main.transform.eulerAngles.x;
        yRotation = Camera.main.transform.eulerAngles.y;
    }

    // Update is called once per frame

    void Update()
    {
        if (Input.GetMouseButton(0))
        {
            float MouseX = Input.GetAxis("Mouse X") * MouseSpeed * Time.deltaTime;
            float MouseY = Input.GetAxis("Mouse Y") * MouseSpeed * Time.deltaTime;

            xRotation -= MouseY;
            yRotation += MouseX;
            

            transform.localRotation = Quaternion.Euler(xRotation, yRotation, 0f);
        }

        float x = Input.GetAxis("Horizontal");
        float z = Input.GetAxis("Vertical");

        Vector3 move = transform.right * x + transform.forward * z;

        controller.Move(move * CameraSpeed * Time.deltaTime);
    }
}
