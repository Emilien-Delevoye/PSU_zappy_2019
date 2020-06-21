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
        yRotation = Camera.main.transform.eulerAngles.y;
        Camera.main.transform.eulerAngles = new Vector3(35f, 0f, 0f);
        xRotation = 35f;
    }

    // Update is called once per frame

    void Update()
    {
        if (Input.GetMouseButton(1))
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
