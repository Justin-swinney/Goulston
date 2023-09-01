let currentImageList = []; // List of images.
let currentLastModified = 0; // Time stamp.

// ** Function below updates and displays modified date.**
function updateModifiedDate(timestamp) {
    const modifiedDateElement = document.getElementById("modified-date");
    modifiedDateElement.textContent = new Date(timestamp * 1000).toLocaleString();
}

// ** Function below filters image list based on search input.**
function filterImageList(imageList, searchInput) {
    return imageList.filter(imageName => {
        const displayName = imageName.split('.').slice(0, -1).join('.').toLowerCase();
        const searchTerms = searchInput.split(/\s+/).filter(term => term.trim() !== '');
        return searchTerms.every(term => displayName.includes(term));
    });
}

// ** Function below filters image list based on search input.**
function updateDisplayedImages() {
    const searchTerm = document.getElementById("search-input").value.toLowerCase();

    const imageTable = document.createElement("table"); // Creating new table to display images.
    const tableContainer = document.getElementById("table-container");
    tableContainer.innerHTML = '';

    let row;

    const filteredImageList = filterImageList(currentImageList, searchTerm);

    filteredImageList.forEach((imageName, index) => {
        if (index % 7 === 0) {
            row = document.createElement("tr");
            imageTable.appendChild(row);
        }

        const imageSrc = "images/" + imageName;
        const displayName = imageName.split('.').slice(0, -1).join('.');

        const td = document.createElement("td");
        td.className = "search-box";

        td.innerHTML = `
            <div class="image-box" onclick="openModal('${imageName}')">
                <img src="${imageSrc}" alt="${imageName}">
                <p>${displayName}</p>
            </div>
        `;

        row.appendChild(td); // Appending table to display images.
    });

    tableContainer.appendChild(imageTable);
}

// ** Function below opens larger image when clicked**
function openModal(imageName) {
    const modal = document.getElementById("modal");
    const modalImage = document.getElementById("modal-image");
    const modalImageName = document.getElementById("modal-image-name"); // Add this line
    const closeModal = document.getElementById("close-modal");

    // Use the original image source directly
    const imageSrc = "images/" + imageName;
    const displayName = imageName.split('.').slice(0, -1).join('.');

    modalImage.src = imageSrc;
    modalImage.alt = displayName;
    modalImageName.textContent = displayName; // Set the text content for the image name
    modal.style.display = "block";

    closeModal.onclick = function () {
        modal.style.display = "none";
    };

    window.onclick = function (event) {
        if (event.target === modal) {
            modal.style.display = "none";
        }
    };
}
document.getElementById("search-input").addEventListener("input", function () {
    updateDisplayedImages(); // Update the displayed images as the user types
});
// ** Function below gets and displays images from directory.**
function fetchAndDisplayImages() {
    fetch("image-list.php")
        .then(response => response.json())
        .then(data => {
            const { imageList, lastModified } = data;

            if (
                JSON.stringify(imageList) !== JSON.stringify(currentImageList) ||
                lastModified !== currentLastModified
            ) {
                currentImageList = imageList;
                currentLastModified = lastModified;
                updateModifiedDate(lastModified);
            }

            updateDisplayedImages(); // Update the displayed images after fetching
        })
        .catch(error => console.error("Error fetching image list:", error));
}

fetchAndDisplayImages();
setInterval(fetchAndDisplayImages, 5000);

<!-- FORMATTING WEBSITE AND APPLYING TIME STAMP FOR DATE MODIFIED -->