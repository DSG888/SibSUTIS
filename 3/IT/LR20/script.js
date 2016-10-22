function convert(form) {
	//получаем данные из поле ввода, преобразуя их в Integer
	base_from = parseInt(form.base_from.value);
	base_to = parseInt(form.base_to.value);
	//преобразуем данные по основанию base_from в десятичную систему
	num = parseInt(form.num.value, base_from);
	//преобразуем данные из десятичной в систему по указанному основанию base_to
	amount = num.toString(base_to);
	//выводим результат
	form.amount.value = amount
}
