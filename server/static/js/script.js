function htmlDecode(input) {
  var doc = new DOMParser().parseFromString(input, "text/html");
  return doc.documentElement.textContent;
}

// Get all checkboxes with type="checkbox"
let checkboxes = document.querySelectorAll('input[type="checkbox"]');

// This took me hours, i eventually just integrated
// it into my backend so i can use vakken.text
vakken = JSON.parse(htmlDecode(vakken.text));

// Define the onchange event handler function
function handleChange(checkbox) {
  checked = checkbox.checked ? "checked" : "unchecked";

  console.log(`Checkbox ${checkbox.id} was ${checked}.`);
}

// Loop through each checkbox and assign the event handler
checkboxes.forEach((checkbox) => {
  checkbox.addEventListener("change", function () {
    handleChange(this);
  });
});
