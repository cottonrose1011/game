using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class QueryChanController : MonoBehaviour
{
    public float speed = 3.0f;
    public float jumpPower = 6.0f;
    private Vector3 direction;
    private CharacterController controller;
    private Animator anim;
    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();
        anim = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        float inputX = Input.GetAxis("Horizontal");
        float inputY = Input.GetAxis("Vertical");
        Vector3 inputDirection = new Vector3 (inputX, 0, inputY);
        direction = Vector3.zero;
        if (inputDirection.magnitude > 0.1f) {
            transform.LookAt(transform.position + inputDirection);
            direction += transform.forward * speed;
            anim.SetFloat("Speed", direction.magnitude);
        }
        else
        {
            anim.SetFloat("Speed", 0);    
        }
      
        controller.Move(direction * Time.deltaTime);
        direction.y += Physics.gravity.y * Time.deltaTime;
    } 
}
