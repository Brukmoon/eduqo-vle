// Odpovědi.
var answers = [ "40", "42", "24", "14" ]

function validateQuiz()
{
	correct = 0;
	x = "";
    for(i = 0; i<answers.length; ++i)
	{
		x = document.forms["quiz"][i].value;
	    if(x == null || x == "")
		{
			alert("Musíte vyplnit všechny kolonky.");
			return false;
		}
		if (x == answers[i])
			++correct;
	}
	alert("Správně bylo " + correct + " odpovědí ze " + answers.length);
	return true;
}