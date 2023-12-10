using System.Collections;
using System.Collections.Generic;
using System.Runtime.ConstrainedExecution;
using UnityEngine;

public class ObstacleMove : MonoBehaviour
{
    public float force = 0.3f;
    public int lifeCount = 0;
    public int END = 3;
    private Transform playerTransform;

    void Start()
    {
        GameObject player = GameObject.FindGameObjectWithTag("PQchan");
        if (player != null)
        {
            playerTransform = player.transform;
        }
        else
        {
            Debug.LogError("PQchan not found!");
        }
    }

    void Update()
    {
        if (playerTransform != null)
        {
            Vector3 playerDirection = playerTransform.position - transform.position;
            transform.position += playerDirection.normalized * force;
        }
    }


    private void OnCollisionEnter(Collision collision)
    {
        lifeCount++;
        if (collision.gameObject.name != "Terrain") // Terrain이 아닌 다른 오브젝트에 대해서만 출력
        {
            Debug.Log(collision.gameObject.name + " 충돌");
            // 이 부분은 플레이어와 충돌했을 때 실행할 내용을 추가하면 됩니다.
        }
        if (lifeCount == END)
        {
            GameObject.Find("GameManager").SendMessage("End");
        }
    }
}
