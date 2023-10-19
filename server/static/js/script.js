function htmlDecode(input) {
  var doc = new DOMParser().parseFromString(input, "text/html");
  return doc.documentElement.textContent;
}

// Get all checkboxes with type="checkbox" and uncheck them
const checkboxes = document.querySelectorAll('input[type="checkbox"]');
for (const checkbox of checkboxes) {
  checkbox.checked = false;
}

// Assign all fieldset id's
const fieldsetElements = ["niveau", "leerjaar", "vak", "methode"].map((x) =>
  document.getElementById(x)
);

// Get vakken directly from the html document
vakken = JSON.parse(htmlDecode(vakken.text));

/**
 * @param {string} url
 * @param {URLSearchParams} params
 */
async function fetchData(url, params) {
  const response = await fetch(url + params);
  const data = await response.text();

  console.log(JSON.parse(data));

  document.getElementById("body-text").innerHTML = data;
}

// Define the onchange event handler function
function handleChange(checkbox) {
  let fieldsets = {};

  // Cycle through all fieldsets
  for (const fieldset of fieldsetElements) {
    const checkeds = fieldset.querySelectorAll("input[type='checkbox']:checked");

    let checkedIDs = [];
    for (const checked of checkeds) {
      let checkedID = checked.id;
      if (checkedID.includes("ander")) {
        checkedID = "anders";
      }
      checkedIDs.push(checkedID.replace("klas-", ""));
    }

    if (checkedIDs.length !== 0) {
      fieldsets[fieldset.id] = checkedIDs.join(",");
    }
  }

  if (fieldsets.length !== 0) {
    fetchData("/q/?", new URLSearchParams(fieldsets));
  }
}

// Loop through each checkbox and assign the event handler
checkboxes.forEach((checkbox) => {
  checkbox.addEventListener("change", function () {
    handleChange(this);
  });
});
