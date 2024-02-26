// Wait for the document to be fully loaded
document.addEventListener("DOMContentLoaded", function () {
  const xValues = ["8-9:59 AM", "10-11:59 AM", "12-1:59 PM", "2-3:59 PM", "4-5:59 PM", "6-7:59 PM"];
  const yValues = [12, 32, 44, 24, 15, 8];
  const barColors = ["red", "green", "blue", "orange", "brown", "purple"];

  new Chart("myChart", {
      type: "bar",
      data: {
          labels: xValues,
          datasets: [{
              backgroundColor: barColors,
              data: yValues
          }]
      },
      options: {
          legend: { display: false },
          title: {
              display: true,
              text: "Today's Shot Data"
          }
      }
  });
});
