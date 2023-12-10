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
        if (collision.gameObject.name != "Terrain") // Terrain�� �ƴ� �ٸ� ������Ʈ�� ���ؼ��� ���
        {
            Debug.Log(collision.gameObject.name + " �浹");
            // �� �κ��� �÷��̾�� �浹���� �� ������ ������ �߰��ϸ� �˴ϴ�.
        }
        if (lifeCount == END)
        {
            GameObject.Find("GameManager").SendMessage("End");
        }
    }
}
