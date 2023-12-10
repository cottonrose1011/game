using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    public GameObject pqchan;
    private Vector3 offset;
    // Start is called before the first frame update
    void Start()
    {
        offset = transform.position - pqchan.transform.position;
    }
    // Update is called once per frame
    void Update()
    {
        transform.position = pqchan.transform.position + offset;
    }
}
