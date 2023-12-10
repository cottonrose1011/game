using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
  
    public GameObject CoverImage;
    public GameObject PlaybackImage;
    public int coinCount = 0;
    public TextMeshProUGUI coinText1;
    public TextMeshProUGUI resultText;

    // Start is called before the first frame update
    void Start()
    {
        PlaybackImage.SetActive(false);
    }
    public void RestartGame()
    {
        SceneManager.LoadScene("SampleScene");
        CoverImage.SetActive(false);
    }
    
    public void OnClickStartButton()
    {
        CoverImage.SetActive(false);
    }

    public void OnClickRestart() {
        RestartGame();
    }

    public void OnClickExit()
    {
        Application.Quit();
    }
    public void End()
    {
        FindObjectOfType<ObstacleMove>().enabled = false;
        resultText.text = "Your Score: " + coinCount;
        PlaybackImage.SetActive(true);
        
    }
    public void GetCoin()
    {
        coinCount++;
        coinText1.text = "Score: " + coinCount;
    }

}
