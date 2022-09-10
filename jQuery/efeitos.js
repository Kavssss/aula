$("document").ready(function(){
	//$("#e1").hide();
	$(".elemento").hide();
	//$("#e3").show(1000);
	//$("#e1").fadeIn(1000);
	//$(".elemento").fadeIn(2000);
	//$(".elemento").fadeOut(1200);


	/*$("#e1").fadeIn(1500, function(){
		$("#e2").fadeIn(1500, function(){
			$("#e3").fadeIn(1500, function(){
				$("#e4").fadeIn(1500);
			});
		});	
	});

	$("#e1").click(function(){
		$("#e2").fadeOut(1500);
	});

	$("#e2").click(function(){
		$("#e1").fadeOut(1500);
	});

	$("#e3").click(function(){
		$("#e1").fadeIn(1500);
	});

	$("#e4").click(function(){
		$("#e2").fadeIn(1500);
	});*/


	//$(".frases").hide();

	$("#frase1").fadeIn(1500, function(){
		$("#frase2").fadeIn(1500, function(){
			$("#frase3").fadeIn(1500, function(){
			});
		});
	});

	$("#frase4").css("cursor", "pointer");
	$("#frase4").css("border", "2px solid #000");

	$("#frase4").hover(function(){
		$("#frase4").css("color", "#ff0000");	
	});

	var naTela;

	$("#frase4").click(function(){
		if (naTela) {
			$("#teste").css("left", "-100%");
			naTela = false;
		} else {
			$("#teste").css("left", "0%");
			naTela = true;
		}
	})









});